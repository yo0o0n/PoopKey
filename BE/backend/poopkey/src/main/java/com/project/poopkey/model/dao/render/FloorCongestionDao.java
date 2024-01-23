package com.project.poopkey.model.dao.render;

import com.project.poopkey.model.dto.render.FloorCongestion;

import java.util.List;

public interface FloorCongestionDao {
    /**층수별 건물 화장실 혼잡도 list를 화면단에 렌더링할 때 사용*/
    List<FloorCongestion> selectList(long buildingId);
}
