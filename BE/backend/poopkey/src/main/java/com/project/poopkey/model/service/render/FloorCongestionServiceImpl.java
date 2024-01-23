package com.project.poopkey.model.service.render;

import com.project.poopkey.model.dao.render.FloorCongestionDao;
import com.project.poopkey.model.dto.render.FloorCongestion;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class FloorCongestionServiceImpl implements FloorCongestionService{

    @Autowired
    private FloorCongestionDao floorCongestionDao;

    @Override
    public List<FloorCongestion> findFloorCongestionList(long buildingId) {
        return floorCongestionDao.selectList(buildingId);
    }
}
