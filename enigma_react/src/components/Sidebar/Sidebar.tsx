import { Link } from "react-router-dom";
import styles from "./styles.module.css";
// Home page and one extra page
const Sidebar = () => {
  return (
    <div className={styles.sidebar}>
      <Link to="/">Home</Link>
      <Link to="/info">About</Link>
    </div>
  );
};

export default Sidebar;
