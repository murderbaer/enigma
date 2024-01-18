import InfoTextBlock from "@components/InfoTextBlock/InfoTextBlock";
import styles from "./styles.module.css";
import { LoremIpsum } from "lorem-ipsum";

function EnigmaInfo() {
  const lorem = new LoremIpsum({
    sentencesPerParagraph: {
      max: 8,
      min: 4,
    },
    wordsPerSentence: {
      max: 16,
      min: 4,
    },
  });

  return (
    <div className={styles.enigmaInfo}>
      <header className={styles.header}>
        <h1>Enigma</h1>
      </header>
      <InfoTextBlock headline="What is the Enigma?">
        <p>{lorem.generateParagraphs(3)}</p>
      </InfoTextBlock>
    </div>
  );
}

export default EnigmaInfo;
