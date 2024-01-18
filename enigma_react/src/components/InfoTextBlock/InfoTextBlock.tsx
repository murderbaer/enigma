import styles from "./styles.module.css";

function InfoTextBlock(props: InfoTextBlockProps) {
  const { headline, children } = props;

  return (
    <div className={styles.infoTextBlock}>
      {headline && <h3>{headline}</h3>}
      {/* ise children */}

      {children}
    </div>
  );
}

type InfoTextBlockProps = {
  headline?: string;
  children: React.ReactNode;
};

export default InfoTextBlock;
