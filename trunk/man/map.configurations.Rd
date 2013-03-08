\name{map.configurations}
\alias{map.configurations}

\title{Find MAP Configurations}

\description{
Find the configurations of the specified nodes that occur with probability \code{pmin} or greater. These configurations are known as most probable configurations or maximum a posteriori (MAP) configurations.
}

\usage{
map.configurations(domain, nodes, pmin)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{nodes}{a character vector specifying by name one or more nodes.}
  \item{pmin}{a single numeric value between 0 and 1 specifying the minimum probability for the most probable configurations.}
}

\value{
a data.frame with one column for each node in \code{nodes}. Each row contains a most probable configuration. The final column of the data.frame (\code{Prob}) gives the probability of the configuration.
}

\references{
HUGIN API Reference Manual \url{http://www.hugin.com/developer/documentation/api-manuals}: \code{RHugin_domain_find_map_configurations}, \code{RHugin_domain_get_number_of_map_configurations}, \code{RHugin_domain_get_map_configuration} and \code{RHugin_domain_get_probability_of_map_configuration}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
demo("asia", echo = FALSE)
compile(asia)
set.finding(asia, "Asia", "yes")
propagate(asia)

map.nodes <- c("Either", "XRay", "Bronchitis", "Tuberculosis")
map.configurations(asia, map.nodes, 0.01)
}

\keyword{programming}


