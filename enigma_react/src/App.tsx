import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import Enigma from "./screens/Enigma/Enigma";
import Sidebar from "./components/Sidebar/Sidebar";

import "./index.css";
import Info from './screens/Info/Info';

export default function App() {
  return (
    <>
      <Router>
        <div className="page">
          <div className="sidebar">
            <Sidebar />
          </div>
          <div className="main">
            <Routes> {/* Use Routes instead of Switch */}
              <Route path="/" element={<Enigma />} />
              <Route path="/info" element={<Info />} />
            </Routes>
          </div>
        </div>
      </Router>
    </>
  );
}
