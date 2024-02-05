import styles from "./StateItem.module.css";

const StateItem = ({
  id,
  report_img,
  report_descript,
  onClick,
  isSelected,
}) => {
  return (
    <div
      onClick={() => onClick(id)}
      className={[
        styles.StateItem,
        isSelected ? styles.StateItem_on_1 : styles.StateItem_off,
      ].join(" ")}
    >
      <img src={report_img} />
      <span>{report_descript}</span>
    </div>
  );
};

export default StateItem;
