package com.project.poopkey.application.main.dao;

import com.project.poopkey.application.main.dto.Restroom;

import java.util.List;

public interface RestroomDao {
    public List<Restroom> selectList(int buildingId);
}
