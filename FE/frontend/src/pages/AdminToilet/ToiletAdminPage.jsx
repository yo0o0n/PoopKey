// ToiletPage.js
import styles from "./ToiletAdminPage.module.css";
import React, { useEffect, useState } from "react";
import axios from "axios";
import FloorBar from "../../components/adminToilet/FloorBar";
import ToiletStatus from "../../components/adminToilet/ToiletStatus";

const ToiletAdminPage = () => {
  const [toiletData, setToiletData] = useState();
  const [selectFloor, setSelectFloor] = useState();

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
    setSelectFloor("1층에 대한 데이터를 삽입");
  }, []);

  return (
    <div className={styles.toiletContainer}>
      <ToiletStatus selectFloor={selectFloor} />
      <FloorBar handleFloorClick={setSelectFloor} toiletData={toiletData} />
    </div>
  );
};

export default ToiletAdminPage;
