package com.project.poopkey.model.dao;

import com.project.poopkey.model.dto.Report;

import java.util.List;

public interface ReportDao {
    public void insert(Report report);
    // 적어도 몇번의 join 과정이 필요.
//    public List<Report> selectList(long);
}
