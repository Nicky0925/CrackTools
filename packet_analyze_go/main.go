package main

import "fmt"

func main() {
  colors := [...]string{"red", "green", "blue"}
  for i, colors := range colors {
    fmt.Println(i, colors)
  }
}
