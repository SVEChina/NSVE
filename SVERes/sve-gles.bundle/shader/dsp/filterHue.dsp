{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/screen.vs",
    "fs" : "shader/code/filter/filterHue.fs",
    "sampler": [ { "name" : "aTexture0", "stage" : 1 , "chn" : 0 } ],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[
                { "name" : "hueAdjust", "type" : "f32", "value" : "0.0" }
            ]
        }
    ]
}
