import { connect } from "react-redux";
import { EnigmaRotor } from "@customTypes/EnigmaType";
import { RootState } from "@redux/store";
import { useDispatch } from "react-redux";
import PlusMinus from "@components/PlusMinus/PlusMinus";

import { EnigmaActions } from "@redux/slices/enigma_slice";

import style from "./styles.module.css";

const mapStateToProps = (state: RootState) => {
  return {
    enigma: state.enigma,
  };
};

type RotorProps = {
  position: number;
  model: number;
  enigma: RootState["enigma"];
};

const RotorComponent = (props: RotorProps) => {
  const { model, enigma, position } = props;
  const rotorCount = enigma.rotors.length;
  const dispatch = useDispatch();
  const rotorValues = Object.keys(EnigmaRotor);
  const currentRotor = rotorValues[model - 1];
  const currentRingSetting = enigma.ringSettings[position];
  const currentRotorPosition = enigma.rotorPositions[position];

  return (
    <div className={style.rotor}>
      <p>Rotor {rotorCount - position}</p>
      <PlusMinus
        onPlus={() =>
          dispatch(
            EnigmaActions.addToRotor({
              position: position,
            })
          )
        }
        onMinus={() =>
          dispatch(
            EnigmaActions.subtractToRotor({
              position: position,
            })
          )
        }
        value={currentRotor}
        label="Rotor"
      />
      <PlusMinus
        onPlus={() =>
          dispatch(
            EnigmaActions.addToRotorPosition({
              position: position,
            })
          )
        }
        onMinus={() =>
          dispatch(
            EnigmaActions.subtractToRotorPosition({
              position: position,
            })
          )
        }
        value={String(currentRotorPosition)}
        label="Rotor Position"
      />
      <PlusMinus
        onPlus={() =>
          dispatch(
            EnigmaActions.addToRingSetting({
              position: position,
            })
          )
        }
        onMinus={() =>
          dispatch(
            EnigmaActions.subtractToRingSetting({
              position: position,
            })
          )
        }
        value={String(currentRingSetting)}
        label="Ring Setting"
      />
    </div>
  );
};

const Rotor = connect(mapStateToProps)(RotorComponent);

export default Rotor;
