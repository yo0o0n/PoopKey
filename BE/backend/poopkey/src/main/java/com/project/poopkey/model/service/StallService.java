package com.project.poopkey.model.service;

import com.project.poopkey.model.dto.Stall;

public interface StallService {
    Stall findStall(long stallId);

    void modifyStall(Stall stall);
}
