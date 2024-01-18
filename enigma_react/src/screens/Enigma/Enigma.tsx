import { connect, useDispatch } from "react-redux";
import { RootState } from "@redux/store";
import Rotor from "@components/Rotor/Rotor";
import Reflector from "@components/Reflector/Reflector";
import { EnigmaType } from "@customTypes/EnigmaType";

import styles from "./styles.module.css";
import TextInput from "@components/TextInput/TextInput";
import { useState } from "react";
import { enigma_post } from "@api/enigma_api";
import { EnigmaActions } from "@redux/slices/enigma_slice";

function setValidMessage(text: string) {
  const upperCaseText = text.toUpperCase();
  const validText = upperCaseText.replace(/[^A-Z]/g, "");

  return validText;
}

function setValidPlugboard(text: string) {
  const upperCaseText = text.toUpperCase();
  const validText = upperCaseText.replace(/[^A-Z]/g, "");

  //don't allow repeated letters
  const uniqueLetters = new Set(validText);
  const uniqueText = [...uniqueLetters].join("");

  return uniqueText;
}

const mapStateToProps = (state: RootState) => {
  return {
    enigma: state.enigma,
  };
};

function EnigmaComponents(props: { enigma: EnigmaType }) {
  const { enigma } = props;
  const dispatch = useDispatch();
  const [encryptedText, setEncryptedText] = useState<string>("");
  const rotors = enigma.rotors.map((rotor: number, index: number) => {
    return <Rotor model={rotor} key={index} position={index} />;
  });
  const disableButton = enigma.plugboard.length % 2 !== 0;

  return (
    <div className={styles.enigma}>
      <h1>Enigma: {enigma.model} </h1>

      <div className={styles.rotors}>
        <Reflector model={enigma.reflector} />
        {rotors}
      </div>
      <TextInput
        text={enigma.message}
        onValueChange={async (value: string) =>
          dispatch(EnigmaActions.setMessage(setValidMessage(value)))
        }
        label="Text to encrypt:"
      />
      <TextInput
        text={enigma.plugboard}
        onValueChange={(value: string) =>
          dispatch(EnigmaActions.setPlugboard(setValidPlugboard(value)))
        }
        label="Plugboard"
      />
      <TextInput text={encryptedText} disabled label="Encrypted text" />
      <button
        onClick={async () => {
          const response = await enigma_post(enigma);
          const json = await response.json();
          setEncryptedText(json.traversedText);
        }}
        disabled={disableButton}
      >
        Encrypt
      </button>
    </div>
  );
}

const Enigma = connect(mapStateToProps)(EnigmaComponents);

export default Enigma;
