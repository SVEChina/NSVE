{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "target-c",
    "vs" : "shader/code/screen.vs",
    "fs" : "shader/code/screen.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[ { "name" : "u_invert", "type" : "fvec2", "value" : "1.0,1.0" } ]
        }
    ]
}
