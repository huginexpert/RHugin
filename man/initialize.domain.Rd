\name{initialize.domain}
\alias{initialize.domain}

\title{Initialize Domain}

\description{
Establish the initial values for all evidence, belief and junction tree tables in an RHugin domain.
}

\usage{
initialize.domain(domain)
}

\arguments{
  \item{domain}{an RHugin domain.}
}

\details{
If an up-to-date memory backup exists (i.e. if \code{save = TRUE} was used in the most recent compilation operation) then the initialization is accomplished simply by loading the tables from the memory backup.  Otherwise, the initial values are recomputed from the conditional probability and utility potentials.  This function erases all previously entered evidence.
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{h_domain_initialize}.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\seealso{
  \code{\link{compile.RHuginDomain}}.
}

\examples{
demo("apple", echo = FALSE)

# Compile the domain
compile(apple)

# Select states
set.finding(apple, "Dry", "no")
set.finding(apple, "Loses", "yes")

# Propagate and get beliefs
propagate(apple)
get.belief(apple, "Sick")

# Initialize the domain
initialize.domain(apple)
}

\keyword{programming}


