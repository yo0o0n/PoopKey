// ToiletPage.js
import styles from "./Home.module.css";
import React, { useEffect, useState, useRef } from "react";
import { getAllBuilding } from "../../util/API";
import { useNavigate } from "react-router-dom";
import LoginHeader from "../../layouts/LoginHeader";

const Home = () => {
  const [buildingData, setBuildingData] = useState();
  const navigate = useNavigate();

  useEffect(() => {
    const getBuildingData = async () => {
      try {
        const response = await getAllBuilding();
        console.log(response);
        setBuildingData(response);
      } catch (e) {
        console.log(e);
      }
    };
    getBuildingData();
  }, []);

  const handleBuildingClick = (buildingId, buildingName) => {
    console.log(buildingId);
    navigate(`/toilet/${buildingId}?name=${buildingName}`);
  };

  return (
    <>
      <LoginHeader />
      <h1>건물 선택이 띄워질 HomePage 입니다.</h1>
      <div>
        <div>
          {buildingData &&
            buildingData.map((building) => (
              <div
                className={styles.building}
                key={building.buildingId}
                onClick={() => {
                  handleBuildingClick(
                    building.buildingId,
                    building.buildingName
                  );
                }}
              >
                {building.buildingName}
              </div>
            ))}
        </div>
      </div>
    </>
  );
};

export default Home;
