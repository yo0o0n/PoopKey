package com.project.poopkey.model.service.render;

import com.project.poopkey.model.dto.render.FloorCongestion;

import java.util.List;

public interface FloorCongestionService {
    List<FloorCongestion> findFloorCongestionList(long buildingId);
}
