import { useEffect, useRef } from "react";
import styles from "./ToiletGrid.module.css";
import { Link, useNavigate } from "react-router-dom";

const ToiletGrid = () => {
  const navigate = useNavigate();
  const items = useRef([]);
  //화장실 데이터 행,열 데이터를 받는다. (axios) -> 온마운트 단계에서 받아와야 함
  const rows = 4;
  const cols = 4;

  //화장실 좌표가 담긴 데이터 (axios) -> 온마운트 단계에서 받아와야 함
  //사용가능:0 사용중:1 고장:2
  const toiletInfo = [
    { stallId: 0, row: 1, col: 1, status: 2 },
    { stallId: 1, row: 1, col: 2, status: 0 },
    { stallId: 2, row: 1, col: 3, status: 0 },
    { stallId: 3, row: 1, col: 4, status: 1 },
  ];

  // aync, await를 통해서 데이터 먼저 가져오기!
  useEffect(() => {
    renderGridItems();
    renderGridToiletItems();
  }, []);

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

  // 화장실칸 id만 넘겨줘서 필요한 데이터는 거기 가서 받던지, 아님 여기서 객체 자체를 넘겨줘도 됨!
  const handleDetailClick = (data) => {
    console.log(data.stallId);
    navigate(`/admin/toiletDetail/${data.stallId}`);
  };

  // 화장실 칸의 좌표를 받아, 격자판에 화장실 칸 위치 표시
  const renderGridToiletItems = () => {
    for (let i = 0; i < toiletInfo.length; i++) {
      const r = toiletInfo[i].row;
      const c = toiletInfo[i].col;
      const s = toiletInfo[i].status;

      // 요소 자체로하는 이유는 직접 속성에 접근해서 바꾸려 했으나 readonly라 통으로 바꿔야 함
      const toilet = items.current.map((item) => {
        // 화장실칸 좌표
        if (item.props.row === r && item.props.col === c) {
          // 화장실칸 현황
          if (s === 0) {
            return (
              <div
                key={item.key}
                style={toiletItemStyle0}
                row={r}
                col={c}
                onClick={() => handleDetailClick(toiletInfo[i])}
              ></div>
            );
          } else if (s === 1) {
            return (
              <div
                key={item.key}
                style={toiletItemStyle1}
                row={r}
                col={c}
                onClick={() => handleDetailClick(toiletInfo[i])}
              ></div>
            );
          } else if (s === 2) {
            return (
              <div
                key={item.key}
                style={toiletItemStyle2}
                row={r}
                col={c}
                onClick={() => handleDetailClick(toiletInfo[i])}
              ></div>
            );
          }
        } else {
          return item;
        }
      });
      items.current = [...toilet];
    }
  };

  //화장실 행과 열을 받아, 화장실 격자판을 만들어주는 함수
  const renderGridItems = () => {
    const gridItems = [];
    let index = 0;
    for (let row = 1; row <= rows; row++) {
      for (let col = 1; col <= cols; col++) {
        gridItems.push(
          <div key={index++} style={itemStyle} row={row} col={col}>
            빈칸
          </div>
        );
      }
    }
    items.current = [...gridItems];
  };

  return <div className={styles.gridContainer}>{items.current}</div>;
};
export default ToiletGrid;
