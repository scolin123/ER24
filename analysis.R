df <- read.csv("outputs/re24.csv")
df$avg_runs <- ifelse(df$pa_count > 0, df$total_runs / df$pa_count, NA)
print(df)