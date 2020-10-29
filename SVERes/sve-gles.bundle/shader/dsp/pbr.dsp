{
    "vdsp" : ["E_V2","E_T0"],
    "pass" : "direct",
    "vs" : "shader/code/pbr/pbr.vs",
    "fs" : "shader/code/pbr/pbr.fs",
    "sampler": [
        { "name" : "u_DiffuseEnvSampler", "stage" : 1 , "chn" : 0 },
        { "name" : "u_SpecularEnvSampler", "stage" : 1 , "chn" : 1 },
        { "name" : "u_brdfLUT", "stage" : 1 , "chn" : 2 },
        { "name" : "u_BaseColorSampler", "stage" : 1 , "chn" : 3 },
        { "name" : "u_NormalSampler", "stage" : 1 , "chn" : 4 },
        { "name" : "u_EmissiveSampler", "stage" : 1 , "chn" : 5 },
        { "name" : "u_MetallicRoughnessSampler", "stage" : 1 , "chn" : 6 },
        { "name" : "u_OcclusionSampler", "stage" : 1 , "chn" : 7 }
    ],
    "uniform": [
        {
            "stage" : 1,
            "bufID" : 1,
            "tbl" :[
                { "name" : "u_LightDirection", "type" : "fvec3", "value" : "null" },
                { "name" : "u_LightColor", "type" : "fvec3", "value" : "null" },
                { "name" : "u_NormalScale", "type" : "f32", "value" : "null" },
                { "name" : "u_EmissiveFactor", "type" : "fvec3", "value" : "null" },
                { "name" : "u_OcclusionStrength", "type" : "f32", "value" : "null" },
                { "name" : "u_MetallicRoughnessValues", "type" : "fvec2", "value" : "null" },
                { "name" : "u_BaseColorFactor", "type" : "fvec4", "value" : "null" },
                { "name" : "u_Camera", "type" : "fvec3", "value" : "null" },
                { "name" : "u_ScaleDiffBaseMR", "type" : "fvec4", "value" : "null" },
                { "name" : "u_ScaleFGDSpec", "type" : "fvec4", "value" : "null" },
                { "name" : "u_ScaleIBLAmbient", "type" : "fvec4", "value" : "null" }
            ]
        }
    ]
}
