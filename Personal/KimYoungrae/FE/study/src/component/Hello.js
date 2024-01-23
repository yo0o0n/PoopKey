import styles from "./Hello.module.css";
import {useState} from 'react';

function Hello(props) {
    console.log(props);
    const [name, setName] = useState("Mike");
    

    return (
        <div>
            <h2 id="name">{name}{props.name}</h2>
            <button onClick={()=>{
                setName(name === "Mike"? "Jane" : "Mike");
            }}>Change</button>
        </div>
    );
}



export default Hello;