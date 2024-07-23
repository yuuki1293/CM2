#r "nuget: MathNet.Numerics.FSharp, 5.0.0"

open System
open System.IO
open System.Numerics
open MathNet.Numerics.IntegralTransforms

let arr = 
    File.ReadAllLines "sample-data.csv"
    |> Array.map float
    |> Array.map (fun f -> Complex (f, 0))

Fourier.Forward arr

arr
|> Array.map _.Magnitude.ToString()
|> fun s -> File.WriteAllLines ("result.csv", s)