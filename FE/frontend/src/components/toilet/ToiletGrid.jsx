import styles from "./ToiletGrid.module.css";
import { useEffect, useState } from "react";
import { useNavigate } from "react-router-dom";
import { getStall } from "../../util/API";

const ToiletGrid = ({ restroom }) => {
  const [stallData, setStallData] = useState(); //화장실정보 + 화장실 칸 list
  const [rows, setRows] = useState(0); // 화장실의 row
  const [cols, setCols] = useState(0); // 화장실의 col
  const [floor, setFloor] = useState(0);
  const navigate = useNavigate();
  //화장실 데이터 행,열 데이터를 받는다. (axios) -> 온마운트 단계에서 받아와야 함

  //화장실 좌표가 담긴 데이터 (axios) -> 온마운트 단계에서 받아와야 함
  //status: 사용가능:0 사용중:1 고장:2
  //content: 빈칸:0 화장실:1 입구:2

  // aync, await를 통해서 데이터 먼저 가져오기!
  useEffect(() => {
    console.log(restroom, "grid 컴포넌트에 전달");
    if (restroom !== undefined) {
      const getStallData = async () => {
        try {
          const response = await getStall(restroom[0].restroomId);
          setStallData(response);
          setRows(response.height);
          setCols(response.width);
          setFloor(response.floor);
          console.log(response.list[1].tissueStatus.length);
        } catch (e) {
          console.log(e);
        }
      };
      getStallData();
    }
  }, [restroom]);
  console.log(restroom, "화장실 정보!!!!!!");

  const itemStyle = {
    //화장실내 전체 style
    boxSizing: "border-box",
    width: `${100 / rows}%`,
    height: `${100 / cols}%`,
    border: "3px solid #ccc",
    visibility: "hidden",
  };

  // 입구
  const enterStyle = {
    boxSizing: "border-box",
    width: `${100 / rows}%`,
    height: `${100 / cols}%`,
    border: "3px solid white",
    backgroundColor: "skyblue",
    borderRadius: "20px",
  };

  // 화장실칸 사용가능 style
  const toiletItemStyle0 = {
    boxSizing: "border-box",
    width: `${100 / rows}%`,
    height: `${100 / cols}%`,
    border: "3px solid white",
    backgroundColor: "green",
    borderRadius: "20px",
    cursor: "pointer",
  };

  // 화장실칸 사용중 style
  const toiletItemStyle1 = {
    boxSizing: "border-box",
    width: `${100 / rows}%`,
    height: `${100 / cols}%`,
    border: "3px solid white",
    backgroundColor: "red",
    borderRadius: "20px",
    cursor: "pointer",
  };

  // 화장실칸 고장 style
  const toiletItemStyle2 = {
    boxSizing: "border-box",
    width: `${100 / rows}%`,
    height: `${100 / cols}%`,
    border: "3px solid white",
    backgroundColor: "yellow",
    borderRadius: "25px",
    cursor: "pointer",
  };

  // 화장실칸 점검중 style
  const toiletItemStyle3 = {
    boxSizing: "border-box",
    width: `${100 / rows}%`,
    height: `${100 / cols}%`,
    border: "3px solid white",
    backgroundColor: "purple",
    borderRadius: "25px",
    cursor: "pointer",
  };

  // 화장실칸 id만 넘겨줘서 필요한 데이터는 거기 가서 받던지, 아님 여기서 객체 자체를 넘겨줘도 됨!
  const handleDetailClick = (data) => {
    console.log(data.stallId);
    navigate(
      `/toiletDetail/${restroom[0].buildingId}/${data.stallId}/${floor}`
    );
  };

  // 화장실 칸의 좌표를 받아, 격자판에 화장실 칸 위치 표시

  return (
    <div className={styles.gridContainer}>
      {stallData &&
        stallData.list.map((item) => {
          if (item.content == 0) {
            //빈칸
            return (
              <div
                key={item.stallId}
                style={itemStyle}
                row={item.row}
                col={item.col}
              >
                빈칸
                {item.tissueStatus.length > 0 && "휴지가 없어"}
              </div>
            );
          } else if (item.content == 2) {
            //입구
            return (
              <div
                key={item.stallId}
                style={enterStyle}
                row={item.row}
                col={item.col}
              >
                입구
                {item.tissueStatus.length > 0 && "휴지가 없어"}
              </div>
            );
          } else if (item.status === 0) {
            return (
              <div
                key={item.stallId}
                style={toiletItemStyle0}
                row={item.row}
                col={item.col}
                onClick={() => handleDetailClick(item)}
              >
                사용가능
                {item.tissueStatus.length > 0 && "휴지가 없어"}
              </div>
            );
          } else if (item.status === 1) {
            return (
              <div
                key={item.stallId}
                style={toiletItemStyle1}
                row={item.row}
                col={item.col}
                onClick={() => handleDetailClick(item)}
              >
                사용중
                {item.tissueStatus.length > 0 && "휴지가 없어"}
              </div>
            );
          } else if (item.status === 2) {
            return (
              <div
                key={item.stallId}
                style={toiletItemStyle2}
                row={item.row}
                col={item.col}
                onClick={() => handleDetailClick(item)}
              >
                고장
                {item.tissueStatus.length > 0 && "휴지가 없어"}
              </div>
            );
          } else if (item.status === 3) {
            return (
              <div
                key={item.stallId}
                style={toiletItemStyle3}
                row={item.row}
                col={item.col}
                onClick={() => handleDetailClick(item)}
              >
                점검중
                {item.tissueStatus.length > 0 && "휴지가 없어"}
              </div>
            );
          }
        })}
    </div>
  );
};
export default ToiletGrid;
