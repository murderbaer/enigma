import { connect, useDispatch } from "react-redux";
import { EnigmaActions } from "@redux/slices/enigma_slice";
import { RootState } from "@redux/store";

import classnames from "classnames";

import style from "./styles.module.css";
import { EnigmaReflector } from "@customTypes/EnigmaType";

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
  const dispatch = useDispatch();

  return (
    <div className={style.reflector}>
      <p>Reflector</p>
      <button
        onClick={() => {
          dispatch(
            EnigmaActions.setReflector({
              model: EnigmaReflector.B,
            })
          );
        }}
        className={classnames(
          style.reflectorButton,
          model === EnigmaReflector.B ? style.active : ""
        )}
      >
        B
      </button>
      <button
        onClick={() => {
          dispatch(
            EnigmaActions.setReflector({
              model: EnigmaReflector.C,
            })
          );
        }}
        className={classnames(
          style.reflectorButton,
          model === EnigmaReflector.C ? style.active : ""
        )}
      >
        C
      </button>
    </div>
  );
};

const Reflector = connect(mapStateToProps)(ReflectorComponent);

export default Reflector;
