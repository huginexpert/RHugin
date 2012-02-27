\name{plot.RHuginDomain}
\alias{plot.RHuginDomain}

\title{Plot an RHugin Domain}

\description{
Plot method for RHugin domain objects.
}

\usage{
\method{plot}{RHuginDomain}(x, y, what = c("network", "jt"), ...)
}

\arguments{
  \item{x}{an RHugin domain.}
  \item{y}{this argument is not used.}
  \item{what}{a character string specifying what to plot.  The choices are \code{"network"} and \code{"jt"} (junction tree).  Note that the domain must be triangulated in order to plot the junction tree.}
  \item{\dots}{additional arguments are ignored.}
}

\details{
This function uses \code{\link{layoutRHugin}} to layout the RHugin domain.  The computed layout is saved in the RHugin domain and will be used by future calls to the plot method and by the Hugin GUI.
}

\value{
\code{x} is invisibly returned.
}

\author{Kjell Konis \email{kjell.konis@me.com}}

\examples{
library(Rgraphviz)

demo("asia", echo = FALSE)
plot(asia)
write.rhd(asia, file = "asia.net", type = "net")

# The layout of the bayesian network in "asia.net" is the same as
# the layout in the R graphic device.

# Compile the domain and plot the junction tree
compile(asia)
plot(asia, what = "jt")
}

\keyword{hplot}


