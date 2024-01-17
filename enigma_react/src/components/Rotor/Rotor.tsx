import { connect } from "react-redux";
import { EnigmaRotor } from "@customTypes/EnigmaType";
import { RootState } from "@redux/store";
import { useDispatch } from "react-redux";

import { EnigmaActions } from "@redux/slices/enigma_slice";

import style from "./styles.module.css";
import "react-dropdown/style.css";
import PlusMinus from "@components/PlusMinus/PlusMinus";

const mapStateToProps = (state: RootState) => {
  return {
    enigma: state.enigma,
  };
};

type RotorProps = {
  position: number;
  model: number;
};

const RotorComponent = (props: RotorProps) => {
  const { model } = props;
  const dispatch = useDispatch();
  const rotorValues = Object.keys(EnigmaRotor);
  const currentRotor = rotorValues[model - 1];

  return (
    <div className={style.rotor}>
      <h3>Rotor {props.position + 1}</h3>
      <PlusMinus
        onPlus={() => dispatch(EnigmaActions.setRotor({ position: props.position, model: (model  % rotorValues.length) +1 }))}
        onMinus={() => {}}
        value={currentRotor}
        label="Rotor"
        />
            <PlusMinus
        onPlus={() => {}}
        onMinus={() => {}}
        value={currentRotor}
        label="Rotor Position"
        />
          <PlusMinus
        onPlus={() => {}}
        onMinus={() => {}}
        value={currentRotor}
        label="Ring Setting"
        />
    </div>
  );
};

const Rotor = connect(mapStateToProps)(RotorComponent);

export default Rotor;
