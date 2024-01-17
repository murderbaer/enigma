import { connect } from "react-redux";
import { EnigmaRotor } from "../../types/EnigmaType";
import { RootState } from "../../redux/store";
import Dropdown from "react-dropdown";

import style from "./styles.module.css";
import "react-dropdown/style.css";

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
  const enigmaRotorKeys = Object.keys(EnigmaRotor);

  return (
    <div className={style.rotor}>
      <Dropdown
        options={enigmaRotorKeys}
        value={enigmaRotorKeys[model - 1]}
        placeholder="Select an option"
      />
    </div>
  );
};

const Rotor = connect(mapStateToProps)(RotorComponent);

export default Rotor;
