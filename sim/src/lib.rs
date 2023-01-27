use nalgebra::{matrix, Vector3};
use rand_distr::{Distribution, Normal};

pub struct Sim {
    state: Vector3<f64>,
    time_step: f64,
    thrust_err: Normal<f64>,
    sensor_err: Normal<f64>,
    rand_force: Normal<f64>,
    thrust: f64,
}

impl Default for Sim {
    fn default() -> Self {
        Self {
            state: Default::default(),
            time_step: 0.01,
            thrust_err: Normal::new(0.0, 2.0).unwrap(),
            sensor_err: Normal::new(0.1, 0.5).unwrap(),
            rand_force: Normal::new(0.0, 5.75).unwrap(),
            thrust: 40.0,
        }
    }
}

impl Sim {
    pub fn tick(&mut self, thrust_percent: f64) {
        let thrust_err = self.thrust_err.sample(&mut rand::thread_rng());
        let rand_force = self.rand_force.sample(&mut rand::thread_rng());
        let thrust_percent = thrust_percent.clamp(0.0, 1.0);
        *self.state.index_mut((2, 0)) =
            self.thrust * thrust_percent + rand_force + thrust_err - 9.81;
        self.state = matrix![
            1.0, self.time_step, 0.5 * self.time_step.powf(2.0);
            0.0, 1.0, self.time_step;
            0.0, 0.0, 1.0
        ] * self.state;
        let y = self.state.index_mut((0, 0));
        *y = y.max(0.0);
        if *y == 0.0 {
            let v = self.state.index_mut((1, 0));
            *v = v.max(0.0);
        }
    }

    pub fn velocity(&self) -> f64 {
        let err = self.sensor_err.sample(&mut rand::thread_rng());
        *self.state.index((1, 0)) + err
    }

    pub fn pos(&self) -> f64 {
        *self.state.index((0, 0))
    }

    pub fn accl(&self) -> f64 {
        let err = self.sensor_err.sample(&mut rand::thread_rng());
        *self.state.index((2, 0)) + err
    }
}
