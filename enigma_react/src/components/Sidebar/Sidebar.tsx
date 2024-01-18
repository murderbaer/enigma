import { Link } from "react-router-dom";
import styles from "./styles.module.css";

const Sidebar = () => {
  return (
    <div className={styles.sidebar}>
      <div className={styles.buttons}>
        <Link to="/">Home</Link>
        <Link to="/enigmaInfo">Enigma Info</Link>
      </div>
    </div>
  );
};

export default Sidebar;
