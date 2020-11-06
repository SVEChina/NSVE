{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/debug/debug2d.vs",
    "fs" : "shader/code/debug/debug.fs",
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[ { "name" : "u_scale", "type" : "fvec2", "value" : "1.0,1.0" },
                     { "name" : "u_off", "type" : "fvec2", "value" : "0.0,0.0" },
                     { "name" : "u_color", "type" : "fvec3", "value" : "0.0,1.0,0.0" } ]
        }
    ]
}
