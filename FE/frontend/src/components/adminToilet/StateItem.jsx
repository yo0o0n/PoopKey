import styles from "./StateItem.module.css";
const StateItem = ({ id, state_img, state_descript, onClick, isSelected }) => {
  return (
    <div
      onClick={() => onClick(id)}
      className={[
        styles.StateItem,
        isSelected ? styles.StateItem_on_2 : styles.StateItem_off,
      ].join(" ")}
    >
      <img src={state_img} />
      <span>{state_descript}</span>
    </div>
  );
};

export default StateItem;
