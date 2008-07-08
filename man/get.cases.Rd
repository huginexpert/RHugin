\name{get.cases}
\alias{get.cases}

\title{Get Cases}

\description{
Retrieve the cases data from an RHugin domain object as a data frame.
}

\usage{
get.cases(domain)
}

\arguments{
  \item{domain}{an RHugin domain object.}
}

\details{
If any of the cases has frequency other than one then a column named \code{Counts} containing the frequency of each case is appended to the output data frame.  If \code{domain} contains a node named \code{counts} there will be a conflict of names.  
}

\value{
A data frame containing the cases from the specified domain.
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{set.cases}}.
}

\examples{
# Create a Hugin domain
ChestClinic <- hugin.domain()

# Add nodes
add.node(ChestClinic, "Asia", states = c("yes", "no"))
add.node(ChestClinic, "Smoking", states = c("yes", "no"))
add.node(ChestClinic, "Tuberculosis", states = c("yes", "no"))
add.node(ChestClinic, "LungCancer", states = c("yes", "no"))
add.node(ChestClinic, "Bronchitis", states = c("yes", "no"))
add.node(ChestClinic, "Either", states = c("yes", "no"))
add.node(ChestClinic, "XRay", states = c("yes", "no"))
add.node(ChestClinic, "Dyspnoea", states = c("yes", "no"))

# Add edges
add.edge(ChestClinic, "Tuberculosis", "Asia")
add.edge(ChestClinic, "LungCancer", "Smoking")
add.edge(ChestClinic, "Bronchitis", "Smoking")
add.edge(ChestClinic, "Either", "Tuberculosis")
add.edge(ChestClinic, "Either", "LungCancer")
add.edge(ChestClinic, "XRay", "Either")
add.edge(ChestClinic, "Dyspnoea", "Either")
add.edge(ChestClinic, "Dyspnoea", "Bronchitis")

# The cases from example 11.1 in the Hugin API Manual
ChestClinic.dat <- data.frame(
  Asia = c("yes", "no", "no", "no", "yes", "yes", "yes", "no"),
  Smoking = c("no", "yes", "yes", "no", "yes", "no", "yes", "no"),
  Dyspnoea = c("no", "yes", "yes", "yes", NA, "no", "yes", "no"),
  XRay = c("no", "no", "yes", "yes", "no", NA, "yes", NA),
  Counts = c(1, 1, 1, 1, 2, 1, 1, 1),
  stringsAsFactors = FALSE)

# Add cases
set.cases(ChestClinic, ChestClinic.dat, "Counts")

# Get cases
get.cases(ChestClinic)
}

\keyword{programming}


