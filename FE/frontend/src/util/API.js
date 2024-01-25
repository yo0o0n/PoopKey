import axios from "axios";

// Connection to BE
export const BASE_URL = "http://localhost:8080";


// 건물 id를 넘겨줬을 때 전체 화장실 데이터 받아오기
// [화장실1, 화장실2, 화장실3....]
// 이 데이터를 받아서 층과 성별로 나눠야함
export const getBuildingData = (id) => {
    axios.get(BASE_URL, {params: {
        id: {id}
    }}).then((res) => {
        console.log(res.data);
    }).catch((e) => {
        console.log("요청 실패")
    }
    );
}

// 화장실 id를 넘겨줬을 때 전체 화장실칸 데이터 받아오기
// [화장실칸1, 화장실칸2, 화장실칸3 ...]
export const getRestRoomData = (id) => {
    axios.get(BASE_URL, {params: {
        id: {id}
    }}).then((res) => {
        console.log(res.data);
    }).catch((e) => {
        console.log("요청 실패")
    }
    );
}

// 화장실칸 id를 넘겨줬을때 해당 화장실칸 정보 받아오기
export const getToiletData = (id) => {
    axios.get(BASE_URL, {params: {
        id: {id}
    }}).then((res) => {
        console.log(res.data);
    }).catch((e) => {
        console.log("요청 실패")
    }
    );
}

// 신고폼 제출 (화장실칸 id, content, select(사유))
export const createDeclarationData = (formData) => {
    axios.post(BASE_URL, formData)
    .then((res) => {
        console.log(res.data)
    }).catch((e) => {
        console.log("신고 제출 실패")
    })
}

// 회원가입
export const createUser = (formData) => {
    axios.post(BASE_URL, formData)
    .then((res) => {
        console.log(res.data)
    }).catch((e) => {
        console.log("회원가입 실패")
    })
}

// 로그인 
export const logInApi = (formData) => {
    axios.post(BASE_URL, formData)
    .then((res) => {
        console.log(res.data)
    }).catch((e) => {
        console.log("로그인 실패")
    })
}