import React, { useState, useEffect } from "react";
import { getRestRoom } from "../util/API";
import { useParams } from "react-router-dom";

export const restroomContext = React.createContext();

// ToiletProvider 태그로 감싼 모든 요소들이 children 변수안에 들어온다.
const ToiletProvider = ({ children }) => {
  // 갱신된 데이터를 받고 싶을 때
  const [restroomData, setRestroomData] = useState();
  const [selectFloor, setSelectFloor] = useState(1);
  const { buildingId } = useParams();
  // 모든 건물의 데이터를 받는 함수

  useEffect(() => {
    const getToiletData = async () => {
      try {
        const response = await getRestRoom(buildingId);
        console.log(response);
        setRestroomData(response);
      } catch (e) {
        console.log(e);
      }
    };
    getToiletData();
  }, []);

  return (
    // context 객체 생성 후 미리 데이터를 넣어둠
    <restroomContext.Provider value={{ restroomData }}>
      {children}
    </restroomContext.Provider>
  );
};
export default ToiletProvider;
