import { connect } from "react-redux";
import { EnigmaRotor } from "@customTypes/EnigmaType";
import { RootState } from "@redux/store";

import style from "./styles.module.css";
import "react-dropdown/style.css";
import PlusMinus from "@components/PlusMinus/PlusMinus";

const mapStateToProps = (state: RootState) => {
  return {
    enigma: state.enigma,
  };
};

type RotorProps = {
  model: number;
};

const RotorComponent = (props: RotorProps) => {
  const { model } = props;
  const rotorValues = Object.values(EnigmaRotor);
  const currentRotor = rotorValues[model];

  return (
    <div className={style.rotor}>
      <PlusMinus
        onPlus={() => {}}
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
