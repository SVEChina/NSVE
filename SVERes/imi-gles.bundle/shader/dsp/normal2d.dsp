{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/normal2d.vs",
    "fs" : "shader/code/normal.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 0,
            "bufID" : 1,
            "tbl" : [
                        { "name" : "matModel", "type" : "fmat4", "value" : "null" },
                        { "name" : "matVP", "type" : "fmat4", "value" : "null" },
                        { "name" : "uInvert", "type" : "fvec2", "value" : "1.0,1.0" }
                    ]
        }
    ]
}
