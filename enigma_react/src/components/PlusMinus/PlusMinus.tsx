import styles from "./styles.module.css";

function PlusMinus(props: PlusMinusProps) {
    const { onPlus, onMinus, value, label } = props;

    return (
        <div className={styles.plusMinus}>
            <label className={styles.label}>{label}</label>
        <button onClick={onMinus}>-</button>
            <span>{value}</span>
            <button onClick={onPlus}>+</button>
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
