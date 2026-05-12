df <- read.csv("outputs/re24.csv")
df$avg_runs <- ifelse(df$pa_count > 0, df$total_runs / df$pa_count, NA)
print(df)

pas <- read.csv("outputs/pas.csv");
player_re24 <- aggregate(runs_scored ~ batter, data = pas, sum)
player_re24 <-  player_re24[order(-player_re24$runs_scored), ]
print(player_re24)