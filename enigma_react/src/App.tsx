import { BrowserRouter as Router, Route, Routes } from "react-router-dom";
import Enigma from "./screens/Enigma/Enigma";
import Sidebar from "./components/Sidebar/Sidebar";
import EnigmaInfo from "@screens/EnigmaInfo/EnigmaInfo";

import "./index.css";

export default function App() {
  return (
    <>
      <Router>
        <div className="page">
          <div className="sidebar">
            <Sidebar />
          </div>
          <div className="main">
            <Routes>
              <Route path="/" element={<Enigma />} />
              <Route path="/enigmaInfo" element={<EnigmaInfo />} />
            </Routes>
          </div>
        </div>
      </Router>
    </>
  );
}
