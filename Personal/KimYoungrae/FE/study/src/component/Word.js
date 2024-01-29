import { useState } from "react";

export default function Word(props) {
    const [isShow, setIsShow] = useState(false);
    const [isDone, setIsDone] = useState(props.word.isDone);
    // state는 해당 컴포넌트에 있는걸 바꿔야지 props는 건드는거 아님 ㅎㅎ

    function toggleShow() {
        setIsShow(!isShow);
    }

    function toggleDone() {
        setIsDone(!isDone);
    }

    return <>
    <tr className={isDone ? "off" : ""} key={props.word.id}>
        <td>
            <input type="checkbox" checked={isDone}
            onChange={toggleDone}></input>
        </td>
        <td>
            {props.word.eng}
        </td>
        <td>
            {isShow && props.word.kor}
            {/* 이거 처음본다. true/false인 isShow와 &&를 한다니! */}
        </td>
        <td>
            <button onClick={toggleShow}>뜻 {isShow ? '숨기기' : '보이기'}</button>
            {/* 이벤트 onClick 꼭 기억하자 */}
            {/* isShow가 true면 숨기기로 나오겠다. */}
            <button className="btn_del">삭제</button>
        </td>
    </tr>
    </>;
}




