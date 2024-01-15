import { connect } from "react-redux";
import { EnigmaReflector } from "../../types/EnigmaType";
import { RootState } from "../../redux/store";
import Dropdown from "react-dropdown";

import style from "./styles.module.css";
import "react-dropdown/style.css";

const mapStateToProps = (state: RootState) => {
  return {
    enigma: state.enigma,
  };
};

type ReflectorProps = {
  model: string;
};

const ReflectorComponent = (props: ReflectorProps) => {
  const { model } = props;
  const reflectorKeys = Object.keys(EnigmaReflector);

  return (
    <div className={style.reflector}>
      <Dropdown options={reflectorKeys} value={model} />
    </div>
  );
};

const Reflector = connect(mapStateToProps)(ReflectorComponent);

export default Reflector;
