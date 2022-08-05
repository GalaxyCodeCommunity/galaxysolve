use std::io::{self, Write};

fn main() {
    print!("Enter a integer number: ");
    io::stdout().flush().unwrap();

    let mut input_text = String::new();
    io::stdin()
        .read_line(&mut input_text)
        .expect("failed to read from stdin");

    let trimmed = input_text.trim();
    match trimmed.parse::<i32>() {
        Ok(i) => {
            for index in 1..i {
                if index % 3 == 0 && index % 5 == 0 {
                    println!("FizzBuzz")
                } else if index % 3 == 0 {
                    println!("Fizz")
                } else if index % 5 == 0 {
                    println!("Buzz")
                } else {
                    println!("{}", index)
                }
            }
        }        
        Err(..) => println!("this was not an integer: {}", trimmed),
    };
}
