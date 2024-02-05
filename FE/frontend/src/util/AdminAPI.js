import axios from "axios";

export const BASE_URL = "http://localhost:8080";

// 화장실 건물등록
export const createRestroom = (data) => {
    axios.post(`${BASE_URL}/api/master/restroom/insert`, data)
    .then((res) => {
        console.log(res);
    }).catch((error) => {
        console.log(error);
    })
}

// 관리자 화장실칸 상태변경
export const updateStatus = (data) => {
    axios.put(`${BASE_URL}/api/master/stalls/update`, data)
    .then((res) => {
        console.log(res);
    }).catch((error) => {
        console.log(error);
    })
}