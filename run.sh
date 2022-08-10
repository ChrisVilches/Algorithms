#!/bin/bash

c++ $1 < data$2 | cpdiff ans$2
