const RegistItem = (props) => {
  const rows = props.height;
  const cols = props.width;

  // 기본 스타일
  const baseStyle = {
    boxSizing: "border-box",
    width: `${Math.min(90 / rows, 90 / cols)}%`,
    height: `${Math.min(90 / rows, 90 / cols)}%`,
    border: "3px solid white",
    borderRadius: "20px",
    cursor: "pointer",
    fontWeight: "bolder",

    display: "flex",
    justifyContent: "space-around",
    alignItems: "center",
  };

  // content 값에 따라 스타일 변경
  let specificStyle;
  let text;
  switch (props.content) {
    case 0:
      specificStyle = {
        ...baseStyle,
        border: "3px solid #ccc",
        backgroundColor: "white",
      };
      text = "빈칸";
      break;
    case 1:
      specificStyle = {
        ...baseStyle,
        backgroundColor: "lightgreen",
      };
      text = "화장실";
      break;
    case 2:
      specificStyle = {
        ...baseStyle,
        backgroundColor: "skyblue",
      };
      text = "입구";
      break;
    default:
      specificStyle = baseStyle;
  }

  return (
    <div {...props} style={specificStyle}>
      {text}
    </div>
  );
};
export default RegistItem;
