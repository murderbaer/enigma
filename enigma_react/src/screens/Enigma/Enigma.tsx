import { connect } from "react-redux";
import { RootState } from "@redux/store";
import Rotor from "@components/Rotor/Rotor";
import Reflector from "@components/Reflector/Reflector";
import { EnigmaType } from "@customTypes/EnigmaType";

import styles from "./styles.module.css";
import TextInput from "@components/TextInput/TextInput";
import { useState } from "react";
import { enigma_post } from "@api/enigma_api";
import { async } from "../../api/enigma_api";

function setValidText(text: string) {
  const upperCaseText = text.toUpperCase();
  const validText = upperCaseText.replace(/[^A-Z]/g, "");

  return validText;
}

const mapStateToProps = (state: RootState) => {
  return {
    enigma: state.enigma,
  };
};

function EnigmaComponents(props: { enigma: EnigmaType }) {
  const { enigma } = props;
  const [text, setText] = useState<string>("");
  const [plugboard, setPlugboard] = useState<string>("");

  const rotors = enigma.rotors.map((rotor: number) => {
    return <Rotor model={rotor} key={rotor} />;
  });

  return (
    <div className={styles.enigma}>
      <h1>Enigma: {enigma.model} </h1>
      <div className={styles.rotors}>
        <Reflector model={enigma.reflector} />
        {rotors}
      </div>
      <TextInput
        text={text}
        onValueChange={(value: string) => setText(setValidText(value))}
        label="Text to encrypt:"
      />
      <TextInput
        text={text}
        onValueChange={(value: string) => setText(setValidText(value))}
        disabled
        label="Encrypted text"
      />
      <TextInput
        text={plugboard}
        onValueChange={(value: string) => setPlugboard(value)}
        label="Plugboard"
      />
      <button
        onClick={async () => {
          const response = await fetch("http://127.0.0.1:17576", {
            method: "POST",

            body: JSON.stringify(enigma),
          });
          console.log(response);

          const data = await response.json();
          console.log(data);
        }}
      >
        Encrypt
      </button>
    </div>
  );
}

const Enigma = connect(mapStateToProps)(EnigmaComponents);

export default Enigma;
