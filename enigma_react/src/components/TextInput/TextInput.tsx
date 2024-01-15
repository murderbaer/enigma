import styles from "./styles.module.css";

function TextInput(props: TextInputProps) {
  const { disabled, text, onValueChange } = props;
  const disabledClass = disabled ? styles.disabled : styles.enabled;
  const labelComponent = props.label ? (
    <label className={styles.label}>{props.label}</label>
  ) : null;

  return (
    <div className={styles.textInputContainer}>
      {labelComponent}
      <input
        type="text"
        value={text}
        onChange={(e) => onValueChange(e.target.value)}
        className={`${styles.textInput} ${disabledClass}`}
        disabled={disabled}
      />
    </div>
  );
}

type TextInputProps = {
  text: string;
  onValueChange: (value: string) => void;
  disabled?: boolean;
  label?: string;
};

export default TextInput;
