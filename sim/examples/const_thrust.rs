use std::time::Duration;

fn main() {
    let mut sim = sim::Sim::default();
    loop {
        sim.tick(0.24);
        println!(
            "y = {} v = {} a = {}",
            sim.pos(),
            sim.velocity(),
            sim.accl()
        );
        std::thread::sleep(Duration::from_millis(10))
    }
}
