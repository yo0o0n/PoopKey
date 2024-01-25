// ToiletPage.js
import React, { useEffect, useState } from "react";
import axios from "axios";
import { Link } from "react-router-dom";
import LoginHeader from "../../layouts/LoginHeader";

const Home = () => {
  const [toiletData, setToiletData] = useState();
  const [selectFloor, setSelectFloor] = useState([]);

  useEffect(() => {
    const getToiletData = async () => {
      try {
        const response = await axios.get(
          "https://jsonplaceholder.typicode.com/posts"
        );
        console.log(response);
        setToiletData(response);
      } catch (e) {
        console.log(e);
      }
    };
    getToiletData();
  }, []);

  return (
    <>
      <LoginHeader />
      <h1>건물 선택이 띄워질 HomePage 입니다.</h1>
    </>
  );
};

export default Home;
