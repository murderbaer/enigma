import styles from "./styles.module.css";

function PlusMinus(props: PlusMinusProps) {
  const { onPlus, onMinus, value, label } = props;

  return (
    <div className={styles.plusMinus}>
      <div className={styles.labelDiv}>
        <label>{label}</label>
      </div>
      <div className={styles.plusMinusButtons}>
        <button onClick={onMinus}>-</button>
        <span>{value}</span>
        <button onClick={onPlus}>+</button>
      </div>
    </div>
  );
}

type PlusMinusProps = {
  onPlus: () => void;
  onMinus: () => void;
  value: string;
  label?: string;
};

export default PlusMinus;
