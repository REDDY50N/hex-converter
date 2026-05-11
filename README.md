# Hex Converter

Simple CLI tool for number conversion between hex, binary and decimal.

## Usage

```
Usage: hex-converter [OPTIONS] <INPUT> 

Example: hex-converter -f hex -i 0x1A3F
         hex-converter -f bin -i 11010101
         hex-converter -f dec -i 12345
         hex-converter 12345 # Default format is decimal
```

## Unit testing

- The core logic is designed as static cmake library, which makes it more easy to test.
- For unit tests we use catch2