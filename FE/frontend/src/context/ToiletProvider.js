import React,{useState, useEffect} from "react";
import { getBuildingData, getRestRoomData, getToiletData} from "../util/API"

export const toiletContext = React.createContext({});

const ToiletProvider = ({children}) => {
    // 갱신된 데이터를 받고 싶을 때
    const [buildingData, setBuildingData] = useState();
    const [restRoomData, setRestRoomData] = useState();
    const [toiletData, setToiletData] = useState();


    async function getBuilding(buildingId){
        const response = await getBuildingData(buildingId);
        setBuildingData(response);
    }

    async function getRestRoom(restRoomId){
        const response = await getRestRoomData(restRoomId);
        setRestRoomData(response);
    }

    async function getToilet(toiletId){
        const response = await getToiletData(toiletId);
        setToiletData(response);

    }

    useEffect(() => {
        //만약 초기에 바로 모든 데이터를 불러와야 한다면 여기에 작성해두기
    },[])

    return (
        <>
        </>
    );

}