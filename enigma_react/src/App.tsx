import { createBrowserRouter, RouterProvider } from "react-router-dom";
import Enigma from "./screens/Enigma/Enigma";
import Sidebar from "./components/Sidebar/Sidebar";

import "./index.css";

const Router = createBrowserRouter([{ path: "/", element: <Enigma /> }]);

export default function App() {
  return (
    <>
      <div className="page">
        <div className="sidebar">
          <Sidebar />
        </div>
        <div className="main">
          <RouterProvider router={Router} />
        </div>
      </div>
    </>
  );
}
