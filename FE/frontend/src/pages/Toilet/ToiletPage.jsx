// ToiletPage.js
import styles from "./ToiletPage.module.css";
import React, { useEffect, useState } from "react";
import { getRestRoom } from "../../util/API";
import { useLocation, useParams } from "react-router-dom";
import FloorBar from "../../components/toilet/FloorBar";
import ToiletStatus from "../../components/toilet/ToiletStatus";

const ToiletPage = () => {
  const { buildingId } = useParams();
  const [restroomData, setRestroomData] = useState();
  const [selectFloor, setSelectFloor] = useState(1);
  const location = useLocation();

  useEffect(() => {
    const getToiletData = async () => {
      try {
        const response = await getRestRoom(buildingId);
        setRestroomData(response);
      } catch (e) {
        console.log(e);
      }
    };
    getToiletData();
  }, [buildingId]);

  useEffect(() => {
    if (location.state != null) {
      setSelectFloor(Number(location.state.floor));
    }
  }, [location]);

  const handleFloorClick = (floor) => {
    setSelectFloor(floor);
  };
  console.log(selectFloor);

  return (
    <div className={styles.toiletContainer}>
      <ToiletStatus selectFloor={selectFloor} restroomData={restroomData} />
      <FloorBar
        handleFloorClick={handleFloorClick}
        restroomData={restroomData}
      />
    </div>
  );
};

export default ToiletPage;
