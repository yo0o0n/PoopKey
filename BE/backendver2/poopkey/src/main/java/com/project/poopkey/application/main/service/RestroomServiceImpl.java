package com.project.poopkey.application.main.service;

import com.project.poopkey.application.main.dao.RestroomDao;
import com.project.poopkey.application.main.dto.Restroom;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class RestroomServiceImpl implements RestroomService{
    @Autowired
    private RestroomDao restroomDao;

    @Override
    public List<Restroom> findRestroomList(int buildingId) {
        return restroomDao.selectList(buildingId);
    }
}
