// App.js
import "./App.css";
import React, { useRef,useEffect, useState } from "react";
import { BrowserRouter, Route, Routes } from "react-router-dom";

import Home from "./pages/Home/Home";
import ToiletPage from "./pages/Toilet/ToiletPage";
import ToiletDetail from "./pages/Toilet/ToiletDetail";
import SignupPage from "./pages/User/SignupPage";
import LoginPage from "./pages/User/LoginPage";

import ToiletAdminPage from "./pages/AdminToilet/ToiletAdminPage";
import ToiletAdminDetatil from "./pages/AdminToilet/ToiletAdminDetail";
import ToiletRegist from "./pages/AdminToilet/ToiletRegist";


const App = () => {
  
  return (
    <div className="app-container">
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Home />}></Route>
          <Route path="/login" element={<LoginPage />}></Route>
          <Route path="/regist" element={<SignupPage/>}></Route>
          <Route path="/toilet/:buildingId" element={<ToiletPage />}></Route>
          <Route path="/toiletDetail/:buildingId/:floor/:stallId" element={<ToiletDetail/>}></Route>

          <Route path="/admin/toilet/:buildingId" element={<ToiletAdminPage />}></Route>
          <Route path="/admin/toiletDetail/:buildingId/:floor/:stallId" element={<ToiletAdminDetatil/>}></Route>
          <Route path="/admin/toiletRegist/:buildingId" element={<ToiletRegist/>}></Route>
        </Routes>
      </BrowserRouter>
    </div>
  );
};

export default App;
