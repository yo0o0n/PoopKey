// App.js
import "./App.css";
import React from "react";
import { BrowserRouter, Route, Routes } from "react-router-dom";
import Home from "./pages/Home/Home";
import ToiletPage from "./pages/Toilet/ToiletPage";
import ToiletDetail from "./pages/Toilet/ToiletDetail";
import SignupPage from "./pages/User/SignupPage";
import LoginPage from "./pages/User/LoginPage";

const App = () => {
  return (
    <div className="app-container">
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Home />}></Route>
          <Route path="/toilet" element={<ToiletPage />}></Route>
          <Route path="/login" element={<LoginPage />}></Route>
          <Route path="/regist" element={<SignupPage/>}></Route>
          <Route path="/toiletDetail/:stallId" element={<ToiletDetail/>}></Route>
        </Routes>
      </BrowserRouter>
    </div>
  );
};

export default App;
